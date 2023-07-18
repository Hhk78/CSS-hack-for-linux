#pragma once

#include <unordered_map>

typedef std::unordered_map<const char*, uintptr_t> PropertyCache;
typedef std::unordered_map<const char*, PropertyCache> ClassCache;

static ClassCache class_cache;

class NetVars {
	private:
		static uintptr_t FindOffset(RecvTable* recv_table, const char* property_name, RecvProp** property_ptr = nullptr) {
			for (int i = 0; i < recv_table->m_nProps; i++) {
				RecvProp& recv_prop = recv_table->m_pProps[i];

				if (strcmp(recv_prop.m_pVarName, property_name) == 0) {
					if (property_ptr)
						*property_ptr = &recv_table->m_pProps[i];

					return recv_prop.m_Offset;
				}

				if (recv_prop.m_RecvType != SendPropType::DPT_DataTable) {
					continue;
				}

				if (uintptr_t offset = FindOffset(recv_prop.m_pDataTable, property_name)) {
					if (property_ptr)
						*property_ptr = &recv_table->m_pProps[i];

					return recv_prop.m_Offset + offset;
				}
			}

			return 0;
		}
	public:
		static uintptr_t GetOffset(const char* class_name, const char* property_name, RecvProp** property_ptr = nullptr) {
			ClassCache::iterator class_cache_itr = class_cache.find(class_name);

			if (class_cache_itr != class_cache.end()) {
				PropertyCache& property_cache = class_cache_itr->second;
				PropertyCache::iterator property_cache_itr = property_cache.find(property_name);
				
				if (property_cache_itr != property_cache.end()) {
					return property_cache_itr->second;
				}
			}
            
			for (ClientClass* class_ptr = clientdll->GetAllClasses(); class_ptr; class_ptr = class_ptr->m_pNext) {
				if (strcmp(class_ptr->m_pNetworkName, class_name) == 0) {
					uintptr_t result = FindOffset(class_ptr->m_pRecvTable, property_name, property_ptr);
					class_cache[class_name][property_name] = result;
					
					return result;
				}
			}

			return 0;
		}
};

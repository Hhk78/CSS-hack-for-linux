    #!/bin/bash
    gdb -n -q -batch -ex "attach $(pidof $1)" \
    	-ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
    	-ex "call \$dlopen(\"$(realpath $2)\", 1)" \
    	-ex "detach" \
    	-ex "quit"

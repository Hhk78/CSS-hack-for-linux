# CSS-hack-for-linux
Counter-Strike:Source için saydam duvar hilesi.

# Bağımlılıkların kurulumu
Debian için:
```bash
sudo dpk --add-architecture i386 && sudo apt update
sudo apt install cmake build-essential gcc-multilib g++-multilib libsdl2-dev libsdl2-dev:i386 gdb
```

Arch için:
```bash
sudo pacman -S cmake base-devel lib32-sdl2 gcc-multilib gdb # you need enable multilib repo
```
# Derleme
```bash
cmake . && make -j4
```
# Kullanım
Derlemeyi başarılı bir şekilde bitirdikten sonra 
```bash
./hile.sh
```
şeklinde enjekte edebilirsiniz. Hile menüsü için insert tuşuna basın.

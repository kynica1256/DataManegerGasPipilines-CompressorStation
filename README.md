**setting dependency of Cereal**
```
git clone https://github.com/USCiLab/cereal.git
cd include
xcopy cereal <your-path> /E

```



**Assembling**
```
g++ -c ObjectTemplate.cpp -o ObjectTemplate.o -I"." -std=c++17


g++ -c main.cpp -o main.o -I"." -std=c++17 && g++ main.o ObjectTemplate.o -o main.exe
```


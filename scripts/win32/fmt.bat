:: makefile
:: cd benchmark   & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
:: cd game        & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
:: cd libng        & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
:: cd test         & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
:: cd third_party  & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..

@echo off
cls

cd benchmark 
FOR /r %%f IN (*.cpp *.hpp) do @clang-format -style=file -i %%f 
cd ..

cd game       
FOR /r %%f IN (*.cpp *.hpp) do @clang-format -style=file -i %%f 
cd ..

cd libng   
FOR /r %%f IN (*.cpp *.hpp) do @clang-format -style=file -i %%f
cd ..

cd test  
FOR /r %%f IN (*.cpp *.hpp) do @clang-format -style=file -i %%f
cd ..

cd third_party 
FOR /r %%f IN (*.cpp *.hpp) do @clang-format -style=file -i %%f 
cd ..
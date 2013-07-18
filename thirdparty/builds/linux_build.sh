echo ------------------------------------------------------
echo ------------------------------------------------------
echo The Green Box
echo building thirdparty libraries
echo generate makefiles
echo ------------------------------------------------------
echo ------------------------------------------------------

echo remove product directiry
rm -r product

echo ------------------------------------------------------
echo ------------------------------------------------------
echo Release ver 
echo ------------------------------------------------------
echo ------------------------------------------------------

rm -r build_workspace
mkdir build_workspace

cd build_workspace
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..

echo ------------------------------------------------------
echo building release
echo ------------------------------------------------------
make
make install
cd ../

echo ------------------------------------------------------
echo ------------------------------------------------------
echo Debug ver 
echo ------------------------------------------------------
echo ------------------------------------------------------

rm -r build_workspace
mkdir build_workspace

cd build_workspace
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..

echo ------------------------------------------------------
echo building release
echo ------------------------------------------------------
make
make install
cd ../

echo doing out...
rm -r build_workspace


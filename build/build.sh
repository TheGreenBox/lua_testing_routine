echo remove product directiry
rm -r -f product

echo create product directory
mkdir product

cd product

echo ------------------------------------------------------
echo building 
echo ------------------------------------------------------

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../ 

echo ------------------------------------------------------
echo building 
echo ------------------------------------------------------

make


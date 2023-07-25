#include <CppTester/Assert.hpp>
#include <CppTester/Tests.hpp>

TestBinary(bootSector, bootSignature, ../bin/boot.bin)
{
    expectBin(bin).memory(510).to.be.equal(0x55);
    expectBin(bin).memory(511).to.be.equal(0xAA);
}
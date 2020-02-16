#include "string/suffix_array.h"
#include "DsAlgorithmsConfig.h"

#include <iostream>

void test_suffix_array_1()
{
    uint32_t N = 11;
    std::string originalStr("sabcabcfabc");
    std::string augStr(originalStr.size() + 1, '$');
    std::memcpy(&augStr[0], &originalStr[0], originalStr.size());

    std::vector<uint32_t> pos = ds_algorithms::string::buildSuffixArray(augStr);
    std::vector<uint32_t> lcp = ds_algorithms::string::buildLcpArray(augStr, pos);
    uint32_t maxRepSubstrLen = 0;
    for (uint32_t l : lcp)
        if (l > maxRepSubstrLen)
            maxRepSubstrLen = l;
    assert(maxRepSubstrLen == 3);   
}

void test_suffix_array_2()
{
    uint32_t N = 18;
    std::string originalStr("trutrutiktiktappop");
    std::string augStr(originalStr.size() + 1, '$');
    std::memcpy(&augStr[0], &originalStr[0], originalStr.size());

    std::vector<uint32_t> pos = ds_algorithms::string::buildSuffixArray(augStr);
    std::vector<uint32_t> lcp = ds_algorithms::string::buildLcpArray(augStr, pos);
    uint32_t maxRepSubstrLen = 0;
    for (uint32_t l : lcp)
        if (l > maxRepSubstrLen)
            maxRepSubstrLen = l;
    assert(maxRepSubstrLen == 4);   
}

void test_suffix_array_3()
{
    uint32_t N = 6;
    std::string originalStr("abcdef");
    std::string augStr(originalStr.size() + 1, '$');
    std::memcpy(&augStr[0], &originalStr[0], originalStr.size());

    std::vector<uint32_t> pos = ds_algorithms::string::buildSuffixArray(augStr);
    std::vector<uint32_t> lcp = ds_algorithms::string::buildLcpArray(augStr, pos);
    uint32_t maxRepSubstrLen = 0;
    for (uint32_t l : lcp)
        if (l > maxRepSubstrLen)
            maxRepSubstrLen = l;
    assert(maxRepSubstrLen == 0);   
}

int main(int argc, char const *argv[])
{
    std::cout << "DsAlgorithms project, version ";
    std::cout << DsAlgorithms_VERSION_MAJOR << "." << DsAlgorithms_VERSION_MINOR;
    std::cout << std::endl;
    try
    {
        test_suffix_array_1();
        test_suffix_array_2();
        test_suffix_array_3();
    }
    catch (const std::exception& ex)
    {
        std::cout << "An exception occured: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
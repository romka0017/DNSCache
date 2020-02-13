#define CATCH_CONFIG_MAIN

#include "libs/catch.hpp"
#include "DNSCache.h"


TEST_CASE("resolve with needed elements", "[resolve]")
{
    DNSCache &dns_cache = DNSCache::getInstance(5);

    dns_cache.update("intel.com", "1.1.1.1");
    dns_cache.update("amd.com", "2.2.2.2");
    dns_cache.update("apple.com", "3.3.3.3");
    dns_cache.update("samsung.com", "4.4.4.4");
    dns_cache.update("huawei.com", "5.5.5.5");

    REQUIRE(dns_cache.resolve("intel.com")   == "1.1.1.1");
    REQUIRE(dns_cache.resolve("amd.com")     == "2.2.2.2");
    REQUIRE(dns_cache.resolve("apple.com")   == "3.3.3.3");
    REQUIRE(dns_cache.resolve("samsung.com") == "4.4.4.4");
    REQUIRE(dns_cache.resolve("huawei.com")  == "5.5.5.5");
}

TEST_CASE("resolve without needed elements", "[resolve]")
{
    DNSCache &dns_cache = DNSCache::getInstance(5);

    dns_cache.update("intel.com", "1.1.1.1");

    REQUIRE(dns_cache.resolve("google.com")  == "");
    REQUIRE(dns_cache.resolve("amd.com")     == "");
    REQUIRE(dns_cache.resolve("apple.com")   == "");
    REQUIRE(dns_cache.resolve("samsung.com") == "");
    REQUIRE(dns_cache.resolve("huawei.com")  == "");
}

TEST_CASE("update with adding of the new element", "[update]")
{
    DNSCache &dns_cache = DNSCache::getInstance(5);

    REQUIRE(dns_cache.resolve("intel.com") == "");
    dns_cache.update("intel.com", "1.1.1.1");
    REQUIRE(dns_cache.resolve("intel.com") == "1.1.1.1");
}


TEST_CASE("update with changing of the existing element", "[update]")
{
    DNSCache &dns_cache = DNSCache::getInstance(5);

    dns_cache.update("intel.com", "1.1.1.1");
    dns_cache.update("amd.com", "2.2.2.2");
    dns_cache.update("apple.com", "3.3.3.3");
    dns_cache.update("samsung.com", "4.4.4.4");
    dns_cache.update("huawei.com", "5.5.5.5");

    REQUIRE(dns_cache.resolve("intel.com") == "1.1.1.1");
    dns_cache.update("intel.com", "1.2.3.4");
    REQUIRE(dns_cache.resolve("intel.com") == "1.2.3.4");
}

TEST_CASE("update with overflow", "[update]")
{
    DNSCache &dns_cache = DNSCache::getInstance(5);

    dns_cache.update("intel.com", "1.1.1.1");
    dns_cache.update("amd.com", "2.2.2.2");
    dns_cache.update("apple.com", "3.3.3.3");
    dns_cache.update("samsung.com", "4.4.4.4");
    dns_cache.update("huawei.com", "5.5.5.5");

    dns_cache.update("google.com", "6.6.6.6");
    REQUIRE(dns_cache.resolve("intel.com") == "");
}

//int main(int argc, char **argv) {
//
//    dns_cache.update("amd.com", "7.7.7.7");
//
//    return 0;
//}
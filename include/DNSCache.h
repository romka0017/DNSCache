#include <string>
#include <list>
#include <unordered_map>
#include <mutex>//for unique_lock
#include <shared_mutex>


class DNSCache
{
public:
    static DNSCache& getInstance(size_t max_size = 0)
    {
        static DNSCache instance;
        if (max_size != 0)
        {
            instance.clear();
            instance.set_max_size(max_size);
        }
        return instance;
    }

    void update(const std::string& name, const std::string& ip);

    std::string resolve(const std::string& name);

private:
    DNSCache() {}

    DNSCache(const DNSCache&) = delete;

    DNSCache& operator=(DNSCache&) = delete;

    void set_max_size(size_t max_size);

    void clear();

    size_t m_max_size = 0;

    std::list<std::pair<std::string, std::string>> m_dq;//ip, name

    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> m_ma;//name, iterator

    std::shared_mutex m_shared_mutex;//common mutex for list and unordered map
};

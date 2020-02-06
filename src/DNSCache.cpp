#include "DNSCache.h"

void DNSCache::set_max_size(size_t max_size)
{
    std::unique_lock<std::shared_mutex> lock(m_shared_mutex);
    m_max_size = max_size;
}

void DNSCache::clear()
{
    std::unique_lock<std::shared_mutex> lock(m_shared_mutex);
    m_dq.clear(), m_ma.clear();
    m_max_size = 0;
}

void DNSCache::update(const std::string& name, const std::string& ip)
{
    std::unique_lock<std::shared_mutex> lock(m_shared_mutex);

    if (m_ma.find(name) == m_ma.end())//no in cache
    {
        if (m_dq.size() == m_max_size)
        {
            std::string lru_element_name = m_dq.back().second;
            m_dq.pop_back();
            m_ma.erase(lru_element_name);
        }
        m_dq.push_front(std::make_pair(ip, name));
        m_ma[name] = m_dq.begin();
    }
    else//in cache
    {
        m_dq.splice(m_dq.begin(), m_dq, m_ma[name]);
        m_dq.begin()->first = ip;
    }
}

std::string DNSCache::resolve(const std::string& name)
{
    std::shared_lock<std::shared_mutex> lock(m_shared_mutex);
    std::string ip;

    auto it = m_ma.find(name);
    if (it != m_ma.end())
        return it->second->first;

    return ip;
}
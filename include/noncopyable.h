#pragma once

class noncopyable
{
protected:
    noncopyable()=default;
    ~noncopyable()=default;
public:
    noncopyable(const noncopyable&)=delete;
    void operator=(const noncopyable&)=delete;
};
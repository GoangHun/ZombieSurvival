#pragma once

template <typename T>
class Singleton
{
public:
    static T& Instance()    //싱글톤
    {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;   //복사 생성자를 지움
    Singleton& operator=(const Singleton&) = delete;    //대입 연산자를 지움

protected:
    Singleton() = default;  //기본 생성자는 뺄 수 없다. 대신 protected에 선언함으로 외부에서 생성할 수 없게 만듬. = {}와 동일
    virtual ~Singleton() = default;
};
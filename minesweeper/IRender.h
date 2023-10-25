#pragma once
class IRender {

public:
    virtual ~IRender() {}
    virtual void Init()=0;
    virtual void BeginRender() = 0;
    virtual void Render() = 0;
    virtual void EndRender() = 0;

};


#pragma once

#include "../Service/Service.h"

class UI {
protected:
    Service* service;

public:
    UI(Service& _service);

    virtual ~UI();

    virtual void startUI() = 0;
};

#pragma once

struct IBindable {
    virtual int bind(void* item) = 0;
};

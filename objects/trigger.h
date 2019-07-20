#ifndef TRIGGER_H
#define TRIGGER_H

#include "Base/visualobject.h"

class Trigger : public VisualObject
{
public:
    Trigger(bool DrawTrigger = true);

    virtual void Init() override;
    virtual void Render() override;

private:
    bool m_DrawTrigger{};
};

#endif // TRIGGER_H

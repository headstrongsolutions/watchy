#ifndef WATCHY_7_SEG_H
#define WATCHY_7_SEG_H

#include <Watchy.h>
#include "Seven_Segment10pt7b.h"
#include "Got725Bd9pt7b.h"
#include "Got725Bd15pt7b.h"
#include "Got725Bd20pt7b.h"
#include "Got725Bd25pt7b.h"
#include "Got725Bd39pt7b.h"
#include "icons.h"

class Watchy7SEG : public Watchy
{
    using Watchy::Watchy;

public:
    void drawWatchFace();
    void drawTime();
    void drawDate();
    void drawSteps();
    void drawWeather();
    void drawBattery();
};

#endif
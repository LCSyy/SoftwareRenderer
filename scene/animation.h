#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
public:
    Animation() {}

    void attachPropertyAnimation(float *property, float start, float end, float step) {
        if(!property) return;
        _property = property;
        _start = start;
        _end = end;
        _step = step;
    }

    void play() {
        if(!_property) return;

        if(_grow) {
            *_property += _step;
        } else {
            *_property -= _step;
        }

        if(*_property < _start) {
            _grow = true;
        } else if(*_property > _end) {
            _grow = false;
        }
    }

private:
    char _padding[3];
    bool _grow{true};
    float _start;
    float _end;
    float _step;

    float *_property{nullptr};
};

#endif // ANIMATION_H

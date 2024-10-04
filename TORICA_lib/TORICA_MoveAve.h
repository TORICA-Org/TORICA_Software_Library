#include <Arduino.h>
#include <stdlib.h>

template <uint8_t N>
class TORICA_MoveAve
{
public:
  TORICA_MoveAve(float value);

  float add(float value);
  float get();

private:
  uint8_t index = 0;

  float _buffer[N];
  float _average = 0;
};

template <uint8_t N>
TORICA_MoveAve<N>::TORICA_MoveAve(float value)
{
  for (uint8_t i = 0; i < N; i++)
  {
    _buffer[i] = value;
  }
  _average = value;
}

template <uint8_t N>
float TORICA_MoveAve<N>::get()
{
  return _average;
}

template <uint8_t N>
float TORICA_MoveAve<N>::add(float value)
{
  _buffer[index] = value;
  index++;
  if (index >= N)
  {
    index = 0;
  }

  _average = 0;
  for (uint8_t i = 0; i < N; i++)
  {
    _average += _buffer[i];
  }
  _average /= N;

  return _average;
}

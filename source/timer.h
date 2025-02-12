typedef uint32_t timespan;

struct Timer{
    timespan targetTime;
    void set(timespan duration);
    timespan getTimeLeft();
    bool isDone();
}
#ifndef UTIL_TIME_H
#define UTIL_TIME_H

/**
 * A singleton object that lives through the entire life cycle of the program
 *
 * Note: Do NOT create your own `Time` object
 */
class Time {
public:
    Time();

    static void Update();

    /**
     * @brief Get the delta time between frames in seconds
     */
    static double GetDeltaTime() { return s_DeltaTime; }

private:
    static double s_Now;
    static double s_Last;

    static double s_DeltaTime;
};

#endif

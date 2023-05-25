
enum Power
{
    off,
    on
};

enum Mode
{
    Auto,
    Fun,
    Dry,
    Cool,
    Heat
};

enum Fan
{
    Quiet,
    Medium,
    Maximum,
    Auto_fun
};
enum Swing_v
{
    Highest,
    High,
    Middle,
    Low,
    Auto_swing
};

struct ACStatus
{
    Power power;
    Mode mode;
    int temp;
    Fan fan;
    Swing_v swing_v;
};

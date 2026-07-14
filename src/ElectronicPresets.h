namespace ObjectPresets
{
    WirePreset BasicWire;
};

struct ElectronicPreset
{
    float powerStorageCapacity = -1;
    float powerFlowRate = -1;
    float operatingPower = -1;
};
struct WirePreset : public ElectronicPreset
{
    float powerStorageCapacity = -1;
    float powerFlowRate = -1;
};

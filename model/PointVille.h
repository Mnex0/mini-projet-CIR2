

class PointVille
{
public:
    PointVille(double lon = 0, double lat = 0)
    {
        this->lon = lon;
        this->lat = lat;

    };
    ~PointVille() {}
    float getLon() const { return this->lon; }
    float getLat() const { return this->lat; }

private:
    float lon;
    float lat;
};
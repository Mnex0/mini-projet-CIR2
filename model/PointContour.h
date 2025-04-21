

class PointContour
{
public:
    PointContour(double lon, double lat)
    {
        this->lon = lon;
        this->lat = lat;
    }
    ~PointContour() {}
    double getLon() const { return this->lon; }
    double getLat() const { return this->lat; }

private:
    double lon;
    double lat;
};
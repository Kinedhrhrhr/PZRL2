#include "min_circle.h"
#include <vector>
#include <cmath>

constexpr double EPS = 1e-8;

bool Point2D::operator==(const Point2D& other) const
{
    return std::abs(x - other.x) < EPS && std::abs(y - other.y) < EPS;
}

bool Point2D::operator!=(const Point2D& other) const 
{
    return !(*this == other);
}

bool Circle::isValid() const 
{
    return radius >= -EPS;
}

bool Circle::contains(const Point2D& point) const
{
    return distance(center, point) <= radius + EPS;
}

bool Circle::contains(const LineSegment& segment) const
{
    return contains(segment.start) && contains(segment.end);
}

bool Circle::containsEntireSegment(const LineSegment& segment) const4
{
    Point2D mid = findMidPoint(segment);
    return contains(segment.start) && contains(segment.end) && contains(mid);
}

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments)
{
    if (segments.empty()) return {{0, 0}, -1.0};
    std::vector<Point2D> points = extractPointsFromSegments(segments);
    Circle res = minCircle(points);
    for (const auto& seg : segments)
    {
        if (!res.containsEntireSegment(seg))
       	{
            Point2D farthestPoint = seg.start;
            double maxDist = 0;
            Point2D mid = findMidPoint(seg);
            
            double d1 = distance(res.center, seg.start);
            if (d1 > maxDist) { maxDist = d1; farthestPoint = seg.start; }
            
            double d2 = distance(res.center, seg.end);
            if (d2 > maxDist) { maxDist = d2; farthestPoint = seg.end; }
            
            double d3 = distance(res.center, mid);
            if (d3 > maxDist) { maxDist = d3; farthestPoint = mid; }

            res = circleFromDiameter(res.center, farthestPoint);
        }
    }
    return res;
}

double distanceSquared(const Point2D& p1, const Point2D& p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

double distance(const Point2D& p1, const Point2D& p2)
{
    return std::sqrt(distanceSquared(p1, p2));
}

Circle circleFromDiameter(const Point2D& p1, const Point2D& p2) 
{
    Point2D mid{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    return {mid, distance(mid, p1)};
}

Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
    double d = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    if (std::abs(d) < EPS) 
    {
        double dist12 = distanceSquared(p1, p2);
        double dist23 = distanceSquared(p2, p3);
        double dist31 = distanceSquared(p3, p1);
        if (dist12 >= dist23 && dist12 >= dist31) return circleFromDiameter(p1, p2);
        if (dist23 >= dist12 && dist23 >= dist31) return circleFromDiameter(p2, p3);
        return circleFromDiameter(p3, p1);
    }

    double centerx = ((p1.x*p1.x + p1.y*p1.y) * (p2.y - p3.y) + (p2.x*p2.x + p2.y*p2.y) * (p3.y - p1.y) + (p3.x*p3.x + p3.y*p3.y) * (p1.y - p2.y)) / d;
    double centery = ((p1.x*p1.x + p1.y*p1.y) * (p3.x - p2.x) + (p2.x*p2.x + p2.y*p2.y) * (p1.x - p3.x) + (p3.x*p3.x + p3.y*p3.y) * (p2.x - p1.x)) / d;

    Point2D center{centerx, centery};
    return {center, distance(center, p1)};
}

Circle minCircle(std::vector<Point2D> points) 
{
    if (points.empty()) return {{0, 0}, -1.0};
    Circle c; c.center = points[0]; c.radius = 0.0;
    for (size_t i = 1; i < points.size(); ++i) {
        if (!c.contains(points[i])){
            c.center = points[i]; c.radius = 0.0;
            for (size_t j = 0; j < i; ++j){
                if (!c.contains(points[j])) {
                    c = circleFromDiameter(points[i], points[j]);
                    for (size_t k = 0; k < j; ++k) 
		    {
                        if (!c.contains(points[k])) { c = circleFrom3Points(points[i], points[j], points[k]);}
                    }}}}}
    return c;
}

std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments) 
{
    std::vector<Point2D> res;
    res.reserve(segments.size() * 3);
    for (const auto& seg : segments) 
    {
        res.push_back(seg.start);
        res.push_back(findMidPoint(seg));
        res.push_back(seg.end);
    }
    return res;
}

Point2D findMidPoint(const LineSegment& segment) 
{
    return {(segment.start.x + segment.end.x) / 2, (segment.start.y + segment.end.y) / 2};
}

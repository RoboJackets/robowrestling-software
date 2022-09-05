#include "simulator/physics/SATCollisionDetector.h" 

std::pair<bool, Vector2f> SATCollisionDetector::CheckCollision(
        RigidBody2d& body1, RigidBody2d& body2) {
    auto axes = GetAxes(body1, body2); 
    std::vector<Vector2f> mtvs; 
    for (auto& axis : axes) {
        auto [body1Max, body1Min] = GetBounds(axis, body1); 
        auto [body2Max, body2Min] = GetBounds(axis, body2); 

        auto isBetweenBounds = [](double val ,double min, double max) {
            return (min <= val && val <= max);  
        };

        if (!(isBetweenBounds(body1Min, body2Min, body2Max) || 
                    isBetweenBounds(body2Min, body1Min, body1Max))) {
            return std::make_pair(false, Vector2f(0,0));
        }

        /* compute overlap */
        double start = (body1Min > body2Min) ? body1Min : body2Min; 
        double end = (body1Max < body2Max) ? body1Max : body2Max; 

        double overlap = end - start; 

        mtvs.push_back(axis.Scale(overlap)); 
    }

    std::sort(mtvs.begin(), mtvs.end(), [](Vector2f& a, Vector2f& b) {
        return std::fabs(a.Norm()) < std::fabs(b.Norm()); 
    });
    
    return std::pair(true, mtvs[0]); 
}

std::array<Vector2f, 4> SATCollisionDetector::GetAxes(RigidBody2d& body1, RigidBody2d& body2) {
    std::array<Vector2f, 4> axes; 

    std::array<Vector2f, 2> body1Sides = GetBodySides(body1); 
    std::array<Vector2f, 2> body2Sides = GetBodySides(body2);


    /* Compute the perpendicular unit vectors for each of the unique sides */
    auto perpendicular = [](Vector2f &u) {
        return u.Perp().Normalize(); 
    };

    std::transform(body1Sides.begin(), body1Sides.end(), body1Sides.begin(), perpendicular);
    std::transform(body2Sides.begin(), body2Sides.end(), body2Sides.begin(), perpendicular); 

    axes[0] = body1Sides[0]; 
    axes[1] = body1Sides[1]; 
    axes[2] = body2Sides[0]; 
    axes[3] = body2Sides[1]; 

    return axes; 
}


std::array<Vector2f, 2> SATCollisionDetector::GetBodySides(RigidBody2d& body) {
    std::array<Vector2f, 2> sides; 
    auto corners = body.GetCorners(); 

    Vector2f topRightPoint    = corners[0];
    Vector2f topLeftPoint     = corners[1]; 
    Vector2f bottomLeftPoint = corners[2];

    sides[0] = topLeftPoint - topRightPoint; 
    sides[1] = bottomLeftPoint - topLeftPoint; 

    return sides; 
}


std::pair<double, double> SATCollisionDetector::GetBounds(
        Vector2f axis, RigidBody2d& body) {

    auto corners = body.GetCorners();
    double max = std::numeric_limits<double>::lowest(); 
    double min = std::numeric_limits<double>::infinity(); 

    for (auto& corner : corners) {
        double dot = Vector2f::DotProduct(corner, axis); 
        max = std::max(max, dot); 
        min = std::min(min, dot); 
    }

    return std::make_pair(max, min); 
}

#include "Math.h"

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
    return a.x * b.y * c.z +
           a.z * b.x * c.y +
           a.y * b.z * c.x -
           a.z * b.y * c.x -
           a.y * b.x * c.z -
           a.x * b.z * c.y;
}

//OŠpŒ`‚Ì“–‚½‚è”»’è
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //1•Ó‚Ì’·‚³‚ğ‹‚ß‚é
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    start.x = start.x - v0.x;
    start.y = start.y - v0.y;
    start.z = start.z - v0.z;
    //u,v,l‚Ì“š‚¦‚ğ‹‚ß‚é
    XMFLOAT3 result = XMFLOAT3{Det(start,e02,dir)/Det(e01,e02,dir),Det(e01,start,dir) / Det(e01,e02,dir),-Det(e01,e02,start) / Det(e01,e02,dir) };

    //u‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
    if (0 <= result.x  && result.x <= 1);
    {
        //v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
        if (0 <= result.y && result.y <= 1)
        {
            //u+v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
            if (result.x + result.y <= 1)
            {
                //l‚Í0‚æ‚è‘å‚«‚¢‚©
                if (0 <= result.z)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

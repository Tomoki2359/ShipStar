#include "Math.h"
#include <math.h>

#include <algorithm>

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
    return a.x * b.y * c.z +
           a.z * b.x * c.y +
           a.y * b.z * c.x -
           a.z * b.y * c.x -
           a.y * b.x * c.z -
           a.x * b.z * c.y;
}

//三角形の当たり判定
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //1辺の長さを求める
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    start.x = start.x - v0.x;
    start.y = start.y - v0.y;
    start.z = start.z - v0.z;
    //u,v,lの答えを求める
    XMFLOAT3 result = XMFLOAT3{Det(start,e02,dir)/Det(e01,e02,dir),Det(e01,start,dir) / Det(e01,e02,dir),-Det(e01,e02,start) / Det(e01,e02,dir) };

    //uの答えが0より大きく1より小さいか
    if (0 <= result.x  && result.x <= 1)
    {
        //vの答えが0より大きく1より小さいか
        if (0 <= result.y && result.y <= 1)
        {
            //u+vの答えが0より大きく1より小さいか
            if (result.x + result.y <= 1)
            {
                //lは0より大きいか
                if (0 <= result.z)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Math::SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

    XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
    float Dist;
    Dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

    XMVECTOR vDir = XMLoadFloat3(&dir);
    vDir = XMVector3Normalize(vDir);
    XMStoreFloat3(&dir, vDir);

    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u, v, l;
    u = Det(d, b, dir) / Det(a, b, dir);
    v = Det(a, d, dir) / Det(a, b, dir);
    l = Det(a, b, d) / Det(a, b, dir);
    if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l <= Dist)
    {
        return true;
    }
    return false;
}

bool Math::SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

    XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
    float Dist;
    Dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

    XMVECTOR vDir = XMLoadFloat3(&dir);
    vDir = XMVector3Normalize(vDir);
    XMStoreFloat3(&dir, vDir);

    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u, v, l;
    u = Det(d, b, dir) / Det(a, b, dir);
    v = Det(a, d, dir) / Det(a, b, dir);
    l = Det(a, b, d) / Det(a, b, dir);

    if (*dist > l && l > 0.0f)
    {
        *dist = l;
    }

    if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l <= Dist)
    {
        return true;
    }
    return false;
}

bool Math::CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMVECTOR vA = XMLoadFloat3(&a), vB = XMLoadFloat3(&b);
    XMVECTOR outer = XMVector3Cross(vA, vB);
    outer = XMVector3Normalize(outer);
    outer = outer * size;
    XMVECTOR vCenter = XMLoadFloat3(&center);
    outer += vCenter;
    XMFLOAT3 fouter;
    XMStoreFloat3(&fouter, outer);
    bool hit = SegmentToPlane(center, fouter, v0, v1, v2);
    return hit;
}

bool Math::CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMVECTOR vA = XMLoadFloat3(&a), vB = XMLoadFloat3(&b);
    XMVECTOR outer = XMVector3Cross(vA, vB);
    outer = XMVector3Normalize(outer);
    outer = outer * size;
    XMVECTOR vCenter = XMLoadFloat3(&center);
    outer += vCenter;
    XMFLOAT3 fouter;
    XMStoreFloat3(&fouter, outer);
    bool hit = SegmentToPlane(center, fouter, v0, v1, v2, dist);
    return hit;
}

void Math::ElasticCollision(XMFLOAT3 pos1, XMVECTOR* vMove1, XMFLOAT3 pos2, XMVECTOR* vMove2)
{
    XMVECTOR vPos1to2 = XMLoadFloat3(&pos2) - XMLoadFloat3(&pos1);
    vPos1to2 = XMVector3Normalize(vPos1to2);
    XMFLOAT3 Pos1to2;
    XMStoreFloat3(&Pos1to2, vPos1to2);
    XMVECTOR vMove1to2 = *vMove2 - *vMove1;
    XMVECTOR v = XMVector3Length(vMove1to2);
    float length = XMVectorGetX(v);
    vMove1to2 = XMVector3Normalize(vMove1to2);
    XMVECTOR vAns;
    vAns = vMove1to2 - vPos1to2;
    XMFLOAT3 Ans;
    XMStoreFloat3(&Ans, vAns);
    Ans.x = Ans.x * Pos1to2.x;
    Ans.y = Ans.y * Pos1to2.y;
    Ans.z = Ans.z * Pos1to2.z;
    vAns = XMLoadFloat3(&Ans);
    *vMove1 += vAns * (length / 2);
    *vMove2 -= vAns * (length / 2);
}

bool Math::InsidePlane(XMFLOAT3 pos, XMFLOAT3 HLt, XMFLOAT3 LwR)
{
    if (HLt.x > LwR.x)
    {
        std::swap(HLt.x, LwR.x);
    }
    if (HLt.y < LwR.y)
    {
        std::swap(HLt.y, LwR.y);
    }
    if (pos.x > HLt.x && pos.x < LwR.x && pos.y < HLt.y && pos.y > LwR.y)
    {
        return true;
    }
    return false;
}

int Math::GetDigits(int value, int m, int n) {
    int val = n + 1;
    int result;

    //n桁目以下の桁を取得
    val = value % (int)pow(10, val);

    //m桁目以上の桁を取得
    result = val / pow(10, m);

    return result;

}

float Math::GetFraction(float value, int m, int n)
{
    if (m > n)
    {
        std::swap(m, n);
    }
    int val;
    float result;
    val = value * pow(10, n);
    val = GetDigits(val, n - 1, m - 1);
    result = val * pow(10, -n);
    return result;
}

float Math::GetNum(float value, int m, int n)
{
    int val = GetDigits(value, 1, n);
    float result = GetFraction(value, 1, m);
    result += val;
    return result;
}

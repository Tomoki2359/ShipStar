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

//�O�p�`�̓����蔻��
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //1�ӂ̒��������߂�
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    start.x = start.x - v0.x;
    start.y = start.y - v0.y;
    start.z = start.z - v0.z;
    //u,v,l�̓��������߂�
    XMFLOAT3 result = XMFLOAT3{Det(start,e02,dir)/Det(e01,e02,dir),Det(e01,start,dir) / Det(e01,e02,dir),-Det(e01,e02,start) / Det(e01,e02,dir) };

    //u�̓�����0���傫��1��菬������
    if (0 <= result.x  && result.x <= 1)
    {
        //v�̓�����0���傫��1��菬������
        if (0 <= result.y && result.y <= 1)
        {
            //u+v�̓�����0���傫��1��菬������
            if (result.x + result.y <= 1)
            {
                //l��0���傫����
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
    //���ʂ̍쐬
    XMFLOAT3 e1 = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 e2 = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    //���ʏ�̓_p�����߂�
    XMFLOAT3 p = XMFLOAT3((e1.x + e2.x) / 2, (e1.y + e2.y) / 2, (e1.z + e2.z) / 2);

    //�_p��������̎n�_�A�I�_���ꂼ��̃x�N�g�����쐬
    XMFLOAT3 p1 = XMFLOAT3(e1.x - p.x, e1.y - p.y, e1.z - p.z);
    XMFLOAT3 p2 = XMFLOAT3(e2.x - p.x, e2.y - p.y, e2.z - p.z);

    //�@���x�N�g�����쐬
    XMVECTOR V1 = XMLoadFloat3(&e1);
    XMVECTOR V2 = XMLoadFloat3(&e2);
    XMVECTOR normal = XMVector3Cross(V1, V2);
    normal = XMVector3Normalize(normal);
    XMFLOAT3 fnormal;
    XMStoreFloat3(&fnormal, normal);

    float pr1 = p1.x * fnormal.x + p1.y * fnormal.y + p1.z * fnormal.z;
    float pr2 = p2.x * fnormal.x + p2.y * fnormal.y + p2.z * fnormal.z;
    if ((pr1 * pr2) <= 0)
    {
        return true;
    }


    return false;
}

#include "Transform.h"

Transform::Transform() :
    matTranslate_(XMMatrixIdentity()),
    matRotate_(XMMatrixIdentity()),
    matScale_(XMMatrixIdentity()),
    position_(XMFLOAT3(0, 0, 0)),
    rotate_(XMFLOAT3(0, 0, 0)),
    scale_(XMFLOAT3(1, 1, 1)),
    pTransform_(nullptr)
{
}

void Transform::Calclation()
{
    //�ړ��s��
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    //��]�s��
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rotateZ * rotateX * rotateY;

    //�g��k���s��
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    Calclation();
    if (pTransform_)    //�e������ꍇ
    {
        return matScale_ * matRotate_ * matTranslate_ * pTransform_->GetWorldMatrix();
    }
    return matScale_ * matRotate_ * matTranslate_;
}
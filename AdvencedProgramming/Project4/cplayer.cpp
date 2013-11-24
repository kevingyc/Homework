#include<string>
#include"cplayer.h"
using namespace std;

CPlayer::CPlayer()
{
	name_ = "";
	identifier_ = 0;
	location_ = 0;
	money_ = 0;
	owned_ = 0;
	isdie_ = false;
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Die()
{
	isdie_ = true;
}

void CPlayer::SetName(const string name)
{
	name_ = name;
}

const std::string CPlayer::GetName()
{
	return name_;	
}

void CPlayer::SetLocation(const int location)
{
	location_ = location;
}

const int CPlayer::GetLocation()
{
	return location_;	
}

void CPlayer::SetMoney(int money)
{
	money_ = money;
}

const int CPlayer::GetMoney()
{
	return money_;	
}

void CPlayer::AddMoney(const int cash)
{
	money_ += cash;
}

void CPlayer::SetIdentifier(const int identifier)
{
	identifier_ = identifier;
}

const int CPlayer::GetIdentifier()
{
	return identifier_;	
}

bool CPlayer::IsDie()
{
	return isdie_;
}

const int CPlayer::GetOwned()
{
	return owned_;
}

void CPlayer::SetOwned(const int owned)
{
	owned_ = owned;
}

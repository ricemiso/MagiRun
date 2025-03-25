#pragma once
class EnemyActionComponent;
class EnemyAction01State
{
public:
	EnemyAction01State(EnemyActionComponent* _belongto) : belongTo_(_belongto) {};
	virtual ~EnemyAction01State() {};
	virtual void enter() = 0;
	virtual EnemyAction01State* update() = 0;
	virtual void exit() = 0;
	EnemyActionComponent* belongTo_;
};
class EnemyAct01StateIncoming : public EnemyAction01State {
public:
	EnemyAct01StateIncoming(EnemyActionComponent* _belngto) : EnemyAction01State(_belngto) {};
	virtual void enter();
	virtual EnemyAction01State* update();
	virtual void exit();
};
class EnemyAct01StateShooting : public EnemyAction01State {
private:
	int shootingtime; //弾撃ちカウント
	ofVec3f movDir;
	int changeDirTime;
public:
	EnemyAct01StateShooting(EnemyActionComponent* _belngto) : EnemyAction01State(_belngto),
		shootingtime(0) {};
	virtual void enter();
	virtual EnemyAction01State* update();
	virtual void exit();
};
class EnemyAct01StateOutgoing : public EnemyAction01State {
	ofVec3f movDir; //脱出方向
public:
	EnemyAct01StateOutgoing(EnemyActionComponent* _belngto) : EnemyAction01State(_belngto),
		movDir({ 0,0,0 }) {};
	virtual void enter();
	virtual EnemyAction01State* update();
	virtual void exit();
};


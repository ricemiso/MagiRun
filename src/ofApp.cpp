#include "ofApp.h"
#include "GameMainCtrlComponent.h"

ofApp* ofApp::instance = nullptr;

ofApp* ofApp::getInstance() {
	assert(instance);
	return instance;
}


//--------------------------------------------------------------
void ofApp::setup(){
	instance = this;

	// �R���W�����}�l�[�W���[
	collisionManager_ = make_unique<CollisionManager>();

	// �T�E���h�}�l�[�W���[
	soundManager_ = make_unique<SoundManager>();

	// ���̓}�l�[�W���[
	inputManager_ = make_unique<InputManager>();

	// �t�H���g�̓ǂݍ���
	auto fontsettings = ofTrueTypeFontSettings("Fonts/mplus-1p-regular.ttf", 16);
	fontsettings.addRanges(ofAlphabet::Latin);
	fontsettings.addRanges(ofAlphabet::Japanese);
	myFont.load(fontsettings);

	// �摜���\�[�X�Ǘ�
	imagesManager_ = make_unique<ResourceManager<ofImage>>();
	imagesManager_->loadContentsFromFile("ImageRes.txt", "Images");

	// �A�j���[�V�������\�[�X�Ǘ�
	animSeqManager_ = make_unique<ResourceManager<AnimSeq>>();
	animSeqManager_->loadContentsFromFile("AnimSeqRes.txt", "AnimSeq");

	// �^�C���f�[�^���\�[�X�Ǘ�
	tileresManager_ = make_unique <ResourceManager<TileData>>();
	tileresManager_->loadContentsFromFile("TileRes.txt", "TileData");

	// �^�C���f�[�^���\�[�X�Ǘ�
	tileres2Manager_ = make_unique <ResourceManager<TileData>>();
	tileres2Manager_->loadContentsFromFile("TileRes.txt", "TileData");

	// �}�b�v�f�[�^���\�[�X�Ǘ�
	mapresManager_ = make_unique <ResourceManager<MapData>>();
	mapresManager_->loadContentsFromFile("MapRes.txt", "MapData");

	hierarchyRoot_ = make_unique<GameActor>();
	hierarchyRoot_->parent_ = nullptr;
	hierarchyRoot_->initialize({0, 0}, "Root");
	hierarchyRoot_->RotAngle() = 0.0f;
	hierarchyRoot_->Scale() = { 1, 1, 1 };

	gameMainCtrlCpnt_ = hierarchyRoot_->addComponent<GameMainCtrlComponent>();
	gameMainCtrlCpnt_->gameStateStart();

	//TODO �R���W�������݂���悤�ɂ���Ƃ�
	//collisionManager_->isDebug_ = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	draworderset_.clear();
	collisionManager_->CaluculateCollide();
	inputManager_->update();
	hierarchyRoot_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ���ˉe�`����s���悤�ɃX�N���[����ݒ肷��
	ofSetupScreenOrtho(ofGetWindowWidth(), ofGetWindowHeight(), -1000, 1000);
	ofPushMatrix();
	ofSetColor(ofColor::white);
	for (auto c : draworderset_) {
		c->draw();
	}
	ofPopMatrix();

	// �f�o�b�O�`��
	collisionManager_->drawDebug();
}

//--------------------------------------------------------------
void ofApp::exit() {
	hierarchyRoot_.reset();
	collisionManager_.reset();
	soundManager_.reset();
	inputManager_.reset();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

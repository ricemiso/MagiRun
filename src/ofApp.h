#pragma once

#include "ofMain.h"
#include "GameActor.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "AnimSeq.h"
#include "TileData.h"
#include "MapData.h"

class GameMainCtrlComponent;

class ofApp : public ofBaseApp{
	private:
		static ofApp* instance;
		
	public:
		static ofApp* getInstance();

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// 全てのゲームアクターの親
		unique_ptr<GameActor> hierarchyRoot_;

		// Manager
		unique_ptr<CollisionManager> collisionManager_;
		unique_ptr<SoundManager>     soundManager_;
		unique_ptr<InputManager>	 inputManager_;
		unique_ptr<ResourceManager<ofImage>>  imagesManager_;
		unique_ptr<ResourceManager<AnimSeq>>  animSeqManager_;
		unique_ptr < ResourceManager<TileData>> tileresManager_;
		unique_ptr < ResourceManager<TileData>> tileres2Manager_;
		unique_ptr < ResourceManager<MapData>>  mapresManager_;

		// Font
		ofTrueTypeFont myFont;

		// GameMain Controller
		GameMainCtrlComponent* gameMainCtrlCpnt_;

		// draw order set
		struct CompFunc {
		public:
			bool operator() (GameActor* _l, GameActor* _r) const {
				return _l->WorldPos().z > _r->WorldPos().z;
			}
		};
		multiset < GameActor*, CompFunc> draworderset_;
};

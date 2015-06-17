//
//  MainScene.cpp
//  testAtest
//
//  Created by kojimatomo on 2015/03/03.
//
//

#include "MainScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "Tja.h"
#include <vector>

USING_NS_CC;


const Vec2 INIT_PLAYER_POSITION = Vec2(40,50);
const int FRUIT_TOP_MARGIN = 45;
const int FONT_SIZE = 23;
const float TIME_LIMIT_SECOND = 60;
const int HIT_X = 50;
const int PERFECT_X = 1;
const int GREAT_X = 2;
const int GOOD_X = 3;
const int PERFECT_SCORE = 3;
const int GREAT_SCORE = 2;
const int GOOD_SCORE = 1;
const int SWIPE_DIFF = 10;
const int SWIPE_WAIT_TIME = 100;
const float SFRAME_RATE = 0.01f;

MainScene::MainScene()
:_score(0)
,_scoreUpWidth(1)
,_scoreLabel(NULL)
,_second(TIME_LIMIT_SECOND)
,_secondLabel(NULL)
,_gameState(GameState::PLAYING)
,_touchLocation(Vec2(0,0))
,_isSwipeTimeUp(0)
,_isSwipeTimeDown(0)
//,_isSwipeTimeLeft(0)
//,_isSwipeTimeRight(0)
,_noteSpeedUserSetting(2.0f)
,_gameTime(0)
{
    
}

MainScene::~MainScene(){
    CC_SAFE_RELEASE_NULL(_scoreLabel);
}

Scene* MainScene::createScene(){
    auto scene = Scene::create();
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool MainScene::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //TJA読み込み
    Tja tja = Tja();
    tja.loadTja();
    _noteTimes = tja.getNoteTimes();
    
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score),
                                                  "Marker Felt",
                                                  FONT_SIZE);
    scoreLabel->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    scoreLabel->enableOutline(Color4B::BLACK, 1.5);
    scoreLabel->setPosition(Vec2(winSize.width / 2 * 1.5, winSize.height - 40));
    this->setScoreLabel(scoreLabel);
    this->addChild(scoreLabel);
    
    auto scoreLabelHeader = Label::createWithSystemFont("SCORE", "Marker Felt", FONT_SIZE);
    scoreLabelHeader->setPosition(Vec2(winSize.width / 2 * 1.5, winSize.height - 20));
    this->addChild(scoreLabelHeader);
    
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second),
                                                   "Marker Felt",
                                                   FONT_SIZE);
    secondLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 40));
    this->setSecondLabel(secondLabel);
    this->addChild(secondLabel);
    
    auto secondLabelHeader = Label::createWithSystemFont("TIME", "Marker Felt", FONT_SIZE);
    secondLabelHeader->setPosition(Vec2(winSize.width / 2, winSize.height - 20));
    this->addChild(secondLabelHeader);
    
    //当たり判定
    auto hitDetection = DrawNode::create();
    hitDetection->drawDot(INIT_PLAYER_POSITION, 10.0f, Color4F(1.0f, 6.0f, 5.0f, 1.0f));
    this->addChild(hitDetection);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event *event){
        this->setTouchLocation(touch->getLocation());
        return true;
    };
    
    listener->onTouchMoved = [this](Touch *touch, Event *event){
        SwipeDirection swipeDirection = this->getSwipeDirection(touch);
        if(swipeDirection != SwipeDirection::NONE){
            
            
            
//            if(swipeDirection == SwipeDirection::RIGHT){
//                if(_isSwipeTimeRight <= 0){
//                    this->initSwipeTime();
//                    this->setIsSwipeTimeRight(SWIPE_WAIT_TIME);
//                    //音
//                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dong.mp3");
//                    //エフェクト
//                    auto explosion = ParticleFire::create();
//                    explosion->setPosition(INIT_PLAYER_POSITION);
//                    explosion->setDuration(0.0001);
            //                    this->addChild(explosion);
//            explosion->setAutoRemoveOnFinish(true); // 表示が終わったら自分を親から削除！
//                }
//            }
//            else if(swipeDirection == SwipeDirection::LEFT){
//                if(_isSwipeTimeLeft <= 0){
//                    this->initSwipeTime();
//                    this->setIsSwipeTimeLeft(SWIPE_WAIT_TIME);
//                    //音
//                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dong.mp3");
//                    //エフェクト
//                    auto explosion = ParticleFire::create();
//                    explosion->setPosition(INIT_PLAYER_POSITION);
            //                    explosion->setDuration(0.0001);
//            explosion->setAutoRemoveOnFinish(true); // 表示が終わったら自分を親から削除！
//                    this->addChild(explosion);
//                }
//            }
            if(swipeDirection == SwipeDirection::UP){
                if(_isSwipeTimeUp <= 0){
                    this->initSwipeTime();
                    this->setIsSwipeTimeUp(SWIPE_WAIT_TIME);
                    //音
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dong.mp3");
                    //エフェクト
                    auto explosion = ParticleFire::create();
                    explosion->setPosition(INIT_PLAYER_POSITION);
                    explosion->setDuration(0.0001);
                    explosion->setAutoRemoveOnFinish(true); // 表示が終わったら自分を親から削除！
                    this->addChild(explosion);
                }
            }
            else if(swipeDirection == SwipeDirection::DOWN){
                if(_isSwipeTimeDown <= 0){
                    this->initSwipeTime();
                    this->setIsSwipeTimeDown(SWIPE_WAIT_TIME);
                    //音
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dong.mp3");
                    //エフェクト
                    auto explosion = ParticleFire::create();
                    explosion->setPosition(INIT_PLAYER_POSITION);
                    explosion->setDuration(0.0001);
                    explosion->setAutoRemoveOnFinish(true); // 表示が終わったら自分を親から削除！
                    this->addChild(explosion);
                }
            }
            this->setTouchLocation(touch->getLocation());
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //this->scheduleUpdate();
    schedule(schedule_selector(MainScene::test), SFRAME_RATE);

    return true;
}

void MainScene::test(float dt){
    this->update(dt);
}

void MainScene::update(float dt){
    if(_gameState == GameState::PLAYING){
        this->autoPlay();
        
        _second -= dt;
        int second = static_cast<int>(_second);
        _secondLabel->setString(StringUtils::toString(second));

        _gameTime++;

        for(std::vector<int>::iterator it = _noteTimes.begin(); it != _noteTimes.end(); it++){
            if(_gameTime == *it-10){
                this->addFruit();
            }
        }
    
        for(auto& fruit: _fruits){
            if(_isSwipeTimeUp == SWIPE_WAIT_TIME
               || _isSwipeTimeDown == SWIPE_WAIT_TIME){
//               || _isSwipeTimeLeft == SWIPE_WAIT_TIME
//               || _isSwipeTimeRight == SWIPE_WAIT_TIME){
                auto hitPosition = INIT_PLAYER_POSITION;
                Rect boundingBox = fruit->getBoundingBox();
                bool isHit = boundingBox.containsPoint(hitPosition);
                if(isHit){
                    this->hitFruit(fruit);
                }
            }
        }
        
        if(_isSwipeTimeUp > 0)		_isSwipeTimeUp--;
        if(_isSwipeTimeDown > 0)	_isSwipeTimeDown--;
//        if(_isSwipeTimeLeft > 0)	_isSwipeTimeLeft--;
//        if(_isSwipeTimeRight > 0)	_isSwipeTimeRight--;
        
        if(_second < 0){
            this->onResult();
        }
    }
}

void MainScene::hitFruit(Sprite *fruit){
    auto fruitPositionX = fruit->getPosition().x;
    log("wa");
    
    if(HIT_X - PERFECT_X < fruitPositionX && fruitPositionX < HIT_X + PERFECT_X){
        _score += PERFECT_SCORE;
    }
    else if(HIT_X - GREAT_X < fruitPositionX && fruitPositionX < HIT_X + GREAT_X){
        _score += GREAT_SCORE;
    }
    else if(HIT_X - GOOD_X < fruitPositionX && fruitPositionX < HIT_X + GOOD_X){
        _score += GOOD_SCORE;
    }
    else{
        //bad
    }
    
    _scoreLabel->setString(StringUtils::toString(_score));
    this->displayHitScore();
    
    this->removeFruit(fruit);
}

Sprite* MainScene::addFruit()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    std::string filename = StringUtils::format("fruit.png");
    auto fruit = Sprite::create(filename);
    
    auto fruitSize = fruit->getContentSize();
    fruit->setPosition(Vec2(winSize.width, FRUIT_TOP_MARGIN));
    this->addChild(fruit);
    _fruits.pushBack(fruit);
    
    auto move = MoveTo::create(_noteSpeedUserSetting, Vec2(0, FRUIT_TOP_MARGIN));
    
    auto remove = CallFuncN::create([this](Node *node){
        auto sprite = dynamic_cast<Sprite *>(node);
        this->removeFruit(sprite);
    });
    
    auto sequence = Sequence::create(move, remove, NULL);
    fruit->runAction(sequence);
    
    return fruit;
}

bool MainScene::removeFruit(Sprite *fruit)
{
    if(_fruits.contains(fruit)){
        fruit->removeFromParent();
        _fruits.eraseObject(fruit);
        return true;
    }
    return false;
}

void MainScene::displayHitScore(){
    auto scoreUpWidthLabel = Label::createWithSystemFont(StringUtils::toString(_scoreUpWidth),
                                                                                "Marker Felt",
                                                                                FONT_SIZE);
    scoreUpWidthLabel->setPosition(INIT_PLAYER_POSITION);
    this->addChild(scoreUpWidthLabel);
    
    auto move = MoveTo::create(1, Vec2(0, 0));
    
    auto remove = CallFuncN::create([this](Node *node){
        auto label = dynamic_cast<Label *>(node);
        label->removeFromParent();
    });
    
    auto sequence = Sequence::create(move, remove, NULL);
    scoreUpWidthLabel->runAction(sequence);
}

void MainScene::onResult(){
    _gameState = GameState::RESULT;
    auto winSize = Director::getInstance()->getWinSize();
    
    auto replayButton =
        MenuItemImage::create("replay_button.png",
                              "replay_button_pressed.png",
                              [](Ref* ref){
                                  auto scene = MainScene::createScene();
                                  auto transition = TransitionFade::create(0.5, scene);
                                  Director::getInstance()->replaceScene(transition);
                              });
    auto titleButton =
        MenuItemImage::create("title_button.png",
                              "title_button_pressed.png",
                              [](Ref* ref){
                                  auto scene = TitleScene::createScene();
                                  auto transition = TransitionFade::create(0.5, scene);
                                  Director::getInstance()->replaceScene(transition);
                              });
    auto menu = Menu::create(replayButton, titleButton, NULL);
    menu->alignItemsVerticallyWithPadding(15);
    menu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(menu);
}

MainScene::SwipeDirection MainScene::getSwipeDirection(Touch *touch){
    auto beforeTouchLocation = this->getTouchLocation();
    auto afterTouchLocation  = touch->getLocation();
    auto diffX = beforeTouchLocation.x - afterTouchLocation.x;
    auto diffY = beforeTouchLocation.y - afterTouchLocation.y;
    if(diffX*diffX > SWIPE_DIFF || diffY*diffY > SWIPE_DIFF){	/* àÍíËãóó£ìÆÇ¢ÇΩÇ∆Ç´ */
        if(diffX*diffX > diffY*diffY){
            if(diffX >= 0){
                return SwipeDirection::RIGHT;
            }
            else{
                return SwipeDirection::LEFT;
            }
        }
        else{
            if(diffY >= 0){
                return SwipeDirection::UP;
            }
            else{
                return SwipeDirection::DOWN;
            }
        }
    }
    return SwipeDirection::NONE;
}

void MainScene::initSwipeTime(){
    this->setIsSwipeTimeUp(0);
    this->setIsSwipeTimeDown(0);
//    this->setIsSwipeTimeLeft(0);
//    this->setIsSwipeTimeRight(0);
}

void MainScene::autoPlay(){
    for(auto& fruit: _fruits){
        for(std::vector<int>::iterator it = _noteTimes.begin(); it != _noteTimes.end(); it++){
            if(_gameTime == *it){
                this->hitFruit(fruit);
            }
        }
    }
}

void MainScene::addBar(){
    auto barNode = DrawNode::create();
    barNode->drawSegment(Vec2(30,300), Vec2(50,300),2.0f, Color4F(.5f, 1.0f, .7f, 1.0f));
    this->addChild(barNode);
    auto move = MoveTo::create(_noteSpeedUserSetting, Vec2(30, 0));
    
    auto remove = CallFuncN::create([this](Node *node){
        auto label = dynamic_cast<Label *>(node);
        label->removeFromParent();
    });
    
    auto sequence = Sequence::create(move, remove, NULL);
    barNode->runAction(sequence);
}

void MainScene::onEnterTransitionDidFinish(){
//    Layer::onEnterTransitionDidFinish();
//    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
}
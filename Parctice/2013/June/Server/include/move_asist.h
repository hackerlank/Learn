#include"command_other_function_all_over.h"

void hero_move_cb(struct event_base *loop, ev_timer* think, int revents);
void wagon_move_cb(struct event_base *loop, ev_timer* think, int revents);
void pet_move_cb(struct event_base *loop, ev_timer* think, int revents);
void mon_move_cb(struct event_base *loop, ev_timer* think, int revents);
void takeGoods_move_cb(struct event_base *loop, ev_timer* think, int revents);
Point getCurrPt(Point &startPt, Point &endPt, Point &speedPt, double t, double& remain);
void view_other_hero_move(Hero* witness, Hero* moveHero);
void view_mon_move(Hero* witness, MonsterBase *mon);
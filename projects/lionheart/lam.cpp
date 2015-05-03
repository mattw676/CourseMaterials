#include "lam.h"
#include <cmath>
#include <iostream>


void lam::Place(int minR,int maxR,int minC,int maxC, SitRep sitrep){
	bool done=false;
	int tr,tc;
	Dir td;
	while(!done){
		tr=minR+rand()%(maxR-minR);	
		tc=minC+rand()%(maxC-minC);	
		if(sitrep.thing[tr][tc].what==space)done=true;
        if(getRank()==crown){
            tc=minC;
            tr=minR;
        }
        if(getRank()==knight){
            tr=minR;
            tc=maxC;
            if(sitrep.thing[tr][tc].what==unit){
                tr=minR+1;
                tc=maxC-1;
                if(sitrep.thing[tr][tc].what==unit){
                    tr=minR+2;
                    tc=maxC-2;
                    if(sitrep.thing[tr][tc].what==unit){
                        tr=maxR-1;
                        tc=maxC;
                        if(sitrep.thing[tr][tc].what==unit){
                            tr=maxR-2;
                            tc=maxC-1;
                            if(sitrep.thing[tr][tc].what==unit){
                                tr=maxR-3;
                                tc=maxC-2;
                            }
                        }
                    }
                }
                
            }
            
        }
        if(getRank()==infantry){
            tr=minR+1;
            tc=maxC;
            if(sitrep.thing[tr][tc].what==unit){
                tr=minR+2;
                tc=maxC-1;
                if(sitrep.thing[tr][tc].what==unit){
                    tr=minR+3;
                    tc=maxC-2;
                    if(sitrep.thing[tr][tc].what==unit){
                        tr=minR+4;
                        tc=maxC-3;
                        //start of bottom half
                        if(sitrep.thing[tr][tc].what==unit){
                            tr=maxR-2;
                            tc=maxC;
                            if(sitrep.thing[tr][tc].what==unit){
                                tr=maxR-3;
                                tc=maxC-1;
                                if(sitrep.thing[tr][tc].what==unit){
                                    tr=maxR-4;
                                    tc=maxC-2;
                                    if(sitrep.thing[tr][tc].what==unit){
                                        tr=maxR-5;
                                        tc=maxC-3;
                                        //other bottom
                                        if(sitrep.thing[tr][tc].what==unit){
                                            tr=maxR-1;
                                            tc=maxC-1;
                                            if(sitrep.thing[tr][tc].what==unit){
                                                tr=maxR-2;
                                                tc=maxC-2;
                                                if(sitrep.thing[tr][tc].what==unit){
                                                    tr=maxR-3;
                                                    tc=maxC-3;
                                                    if(sitrep.thing[tr][tc].what==unit){
                                                        tr=maxR-4;
                                                        tc=maxC-4;
                                                        //other top
                                                        if(sitrep.thing[tr][tc].what==unit){
                                                            tr=minR;
                                                            tc=maxC-1;
                                                            if(sitrep.thing[tr][tc].what==unit){
                                                                tr=minR+1;
                                                                tc=maxC-2;
                                                                if(sitrep.thing[tr][tc].what==unit){
                                                                    tr=minR+2;
                                                                    tc=maxC-3;
                                                                    if(sitrep.thing[tr][tc].what==unit){
                                                                        tr=minR+3;
                                                                        tc=maxC-4;
                                                                        if(sitrep.thing[tr][tc].what==unit){
                                                                            tr=minR+1;
                                                                            tc=minC;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(getRank()==archer){
            tc=minC+2;
            tr=maxR-4;
            if(sitrep.thing[tr][tc].what==unit){
                tc=minC+1;
                tr=maxR-5;
                if(sitrep.thing[tr][tc].what==unit){
                    tc=minC;
                    tr=maxR-5;
                    //start of top
                    if(sitrep.thing[tr][tc].what==unit){
                        tc=maxC-3;
                        tr=minR+3;
                        if(sitrep.thing[tr][tc].what==unit){
                            tc=maxC-4;
                            tr=minR+4;
                            if(sitrep.thing[tr][tc].what==unit){
                                tc=maxC-5;
                                tr=minR+4;
                            }
                        }
                    }
                }
            }
        }
	}
	int rdist=ROWS/2-tr;
	int cdist=COLS/2-tc;
	if(abs(rdist)<abs(cdist)){
		if(cdist>0)td=rt;
		else td=lt;
	}else{
		if(rdist>0)td=up;
		else td=dn;
	}
	r=tr;
	c=tc;
	dir=td;
}


// tell someone what you want to do
Action lam::Recommendation(SitRep sitrep){
	
	// this code is provided as an example only
	// use at your own risk
	Action a; 

	// first, try to attack in front of you
	int tr=r,tc=c;
	switch(dir){
	case up: tr--; break;
	case dn: tr++; break;
	case rt: tc++; break;
	case lt: tc--; break;
	case none: break;
	}
    if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS){
        if(sitrep.thing[tr][tc].what==unit){
            if(sitrep.thing[tr][tc].tla==tla){
                a.action=turn;
                a.dir=dn;
                a.ar=tr;
                a.ac=tc;
                return a;
            }
        }
    }
	if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS){
		if(sitrep.thing[tr][tc].what==unit){
			if(sitrep.thing[tr][tc].tla!=tla){
				a.action=attack;
				a.ar=tr;
				a.ac=tc;
				return a;
			}
		}
	}	
	// there is not an enemy in front of me
	// so head to the nearest enemy
	if(rank==knight||rank==infantry||rank==archer){
        if(dir==sitrep.nearestEnemy.dirFor){
            a.dir=sitrep.nearestEnemy.dirFor;
            a.action=fwd;
            a.maxDist=1;
            if(rank==knight||rank==crown)a.maxDist=HORSESPEED;
            return a;
        } else {
            a.action=turn;
            a.dir=sitrep.nearestEnemy.dirFor;
            return a;
        }
    }
    if(rank==crown){
        a.dir=up;
        a.action=turn;
        a.action=fwd;
        return a;
    }
	a.action=nothing;
	return a;
	
}

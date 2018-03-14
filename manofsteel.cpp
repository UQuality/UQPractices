#include<bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl

using namespace std;
double eps = 1e-6;

struct circle{
	int x, y, r;
	circle(int _x, int _y, int _r){
		x = _x;
		y = _y;
		r = _r;
	}
	circle(){}
};

struct line{
	double a, b, c;
	line(double sx, double sy, double tx, double ty){
		if(sx == tx){
			a = 1;
			b = 0;
			c = -sx;
		}
		else{
			b = 1;
			a = -(sy - ty) / (sx - tx);
			c = -(a * sx) - (b * sy);
		}
	}
	line(double m, double cx, double cy){
		a = -m;
		b = 1;
		c = -(a*cx) - (b * cy);
	}
};

circle ps[105];

double dist(double x1, double y1, double x2, double y2){
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

pair<double,double> intersect(line l1, line l2){
	double x, y;
	x = (l2.b*l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a*l2.b);
	if(fabs(l1.b) > eps)
		y = -(l1.a * (x) + l1.c) / l1.b;
	else
		y = -(l2.a * (x) + l2.c) / l2.b;
	return make_pair(x,y);
}

pair<double, double> closestPoint(line l, double cx, double cy){
	double x, y;
	if(fabs(l.b) <= eps){
		x = -(l.c);
		y = cy;
		return make_pair(x,y);
	}
	if(fabs(l.a) <= eps){
		x = cx;
		y = -(l.c);
		return make_pair(x,y);
	}
	line perp = line(1/l.a,cx, cy);
	return intersect(l,perp);
}

int main(){
	int n;
	double cx, cy, sx, sy, tx, ty, r;
	int cas = 1, obs;
	while(cin >> sx >> sy >> tx >> ty &&
		(sx != 0 or sy != 0 or tx != 0 or ty != 0)){
		line l(sx,sy,tx,ty);
		obs = 0;
		double tot = dist(sx,sy,tx,ty);
		//debug(tot);
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> cx >> cy >> r;
			ps[i] = circle(cx,cy,r);
		}
		circle cur; double h;
		for(int i = 0; i < n; i++){
			cur = ps[i];
			pair<double,double> p = closestPoint(l,cur.x, cur.y);
			h = dist(cur.x, cur.y, p.first, p.second);
			//debug(h);
			if(h < cur.r){
                obs ++;
				double op = sqrt(cur.r* cur.r - h*h);
				//debug(op);
				tot -= op*2;
				double tetha = acos(h / cur.r);
				double arlen = cur.r * (tetha);
                //debug(arlen);
				tot += 2*arlen;
			}
		}
		cout << "Case " << cas++ << " : " << obs << " " << fixed << setprecision(2) << tot << "\n";
	}
	return 0;
}

#include <iostream>
#include <algorithm>
#include <cstring>
const int x = 10;   //vertex no.


const int colors[x] = { 0,1,2,3,4,5,6,7,8,9 };
int counter = 0;
bool problem = false;

/*  Example graph
	 B      G---------J
	/ \      \        |
       /   \      \       |
      /     \      \      |
     A------C-------E-----K
     \     /       /      |
      \   /       /       |
       \ /       /        |
        D-------F---------L

*/

bool graf[x][x] = { //adj. matrix
	0,1,1,1,0,0,0,0,0,0,
	1,0,1,0,0,0,0,0,0,0,
	1,1,0,1,1,0,0,0,0,0,
	1,0,1,0,0,1,0,0,0,0,
	0,0,1,0,0,1,1,0,1,0,
	0,0,0,1,1,0,0,0,1,1,
	0,0,0,0,1,0,0,1,0,0,
	0,0,0,0,0,0,1,0,1,0,
	0,0,0,0,1,0,0,1,0,1,
	0,0,0,0,0,1,0,0,1,0
};

char vertex_names[x] = {'A','B','C','D','E','F','G','J','K','L'};
int rate_list[x]; //{ 0,0,0,0,0,0,0,0,0,0};

struct Graf {
	char vertex_id[x];
	int vertex_rates[x];
	bool adj[x][x];
	int colors[x];
	bool colored[x];
};

//welsh powell

void colorIt(Graf g) {
	counter++;
	int biggest=0;
	int temp_rate = 0;

	//rate listing from adj matrix (counting edges)

	if (counter == 1)
		for (int i = 0; i < x; i++)
			for (int j = 0; j < x; j++)
				if (g.adj[i][j])
					rate_list[i]++;


	for (int w = 0; w < x; w++)
		if (!g.colored[w]) {
			g.vertex_rates[w] = rate_list[w];
			if (temp_rate < g.vertex_rates[w]) {
				temp_rate = g.vertex_rates[w];
				biggest = w;
			}
		}

	//coloring biggest one first

	g.colors[biggest] = colors[counter];
	std::cout << g.vertex_id[biggest] <<":color "<< g.colors[biggest]<<std::endl;

	//coloring which doesn't have path with biggest one

	for (int e=0;e < x;e++)
		if (!g.adj[biggest][e] && biggest!=e && !g.colored[e]) {
			for (int t = 0; t < x;t++) {

				if(g.adj[e][t] &&g.colors[t]==g.colors[biggest]) problem = true;

					if (t == x - 1 && !problem) {
						g.colors[e] = colors[counter];
						std::cout << g.vertex_id[e] <<":color "<< g.colors[e] << std::endl;
						g.colored[e] = true;
						problem = false;
					}
					else if (t == x - 1) problem = false;
			}
		}

		g.colored[biggest] = true;

	//somehow it gives sometimes "access violation" error

	if (std::all_of(std::begin(g.colored), std::end(g.colored), [](bool i) { return i; })) {
		std::cout << "Graph full colored" << std::endl;
		system("pause");
		exit(EXIT_SUCCESS);

	}

	else colorIt(g); //recusive because too lazy to sort :)

}

int main()
{
	Graf graf1;

	//init color

	for (int y = 0; y < x; y++) {
		graf1.colors[y] = 99;
		graf1.colored[y] = false;
	}

	//init graph
	memcpy(&graf1.adj, &graf, sizeof(graf1.adj));
	memcpy(&graf1.vertex_id, &vertex_names, sizeof(graf1.vertex_id));

	colorIt(graf1);

	return 0;
}

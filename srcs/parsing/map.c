#include "doom.h"

/*
** Verify that vertexes are chained
*/
int     verify_vertex(t_engine *e)
{
	unsigned	iter;
	t_vtx		*vertex;
	t_sector	*sect;

	iter = 0;
	while (iter < e->nsectors)
    {
		sect = &e->sectors[iter];
        vertex = sect->vertex;

        if (vertex[0].x != vertex[sect->npoints].x
        	|| vertex[0].y != vertex[sect->npoints].y)
            fprintf(stderr, "Internal error: Sector %u: Vertexes don't form a loop!\n", iter);
		iter++;
    }
	return (1);
}

/*
** Verify that sectors are bounded together if 
** they share an edge
*/
int		verify_bounded_neighbor(t_engine *e, t_chain *chain, t_edge *edge, int *found)
{
	const t_sector	*sect = &e->sectors[chain->a];
	t_sector		*neigh;

	while (chain->d < e->nsectors)
	{
		neigh = &e->sectors[chain->d];
		chain->c = 0;
		while (chain->c < neigh->npoints)
		{
			if (equal_vertex(neigh->vertex[chain->c + 1], edge->v1)
				&& equal_vertex(neigh->vertex[chain->c], edge->v2))
			{
				if (neigh->neighbors[chain->c] != (int)chain->a)
				{
					fprintf(stderr, "Sector %d: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
						chain->d, edge->v2.x,edge->v2.y, edge->v1.x,edge->v1.y, chain->a, neigh->neighbors[chain->c]);
					neigh->neighbors[chain->c] = chain->a;
					return (1);
				}
				if (sect->neighbors[chain->b] != (int)chain->d)
				{
					fprintf(stderr, "Sector %u: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
						chain->a, edge->v1.x, edge->v1.y,edge->v2.x, edge->v2.y, chain->d, sect->neighbors[chain->b]);
					sect->neighbors[chain->b] = chain->d;
					return (1);
				}
				else
					++*found;
			}
			chain->c++;
		}
		chain->d++;
	}
	return (0);
}

/*
** Verify neighbors of vertexes and fix them
*/
int		verify_neighbor(t_engine *e, t_sector *sect, t_vtx *vert)
{
	t_chain		chain;
	t_edge		edge;
	int			found;

	chain.a = 0;
	while (chain.a < e->nsectors)
	{
		sect = &e->sectors[chain.a];
		vert = sect->vertex;
		chain.b = 0;
		while (chain.b < sect->npoints)
		{
			if (sect->neighbors[chain.b] >= (int)e->nsectors)
			{
				fprintf(stderr, "Sector %u: Contains neighbor %d (too large, number of sectors is %u)\n",
					chain.a, sect->neighbors[chain.b], e->nsectors);
			}
			edge = (t_edge){vert[chain.b], vert[chain.b +1]};
			found = 0;
			chain.d = 0;
			if (verify_bounded_neighbor(e, &chain, &edge, &found))
				return (verify_map(e));
			if (sect->neighbors[chain.b] >= 0 && sect->neighbors[chain.b] < (int)e->nsectors && found != 1)
				fprintf(stderr, "Sectors %u and its neighbor %d don't share line (%g,%g)-(%g,%g)\n",
					chain.a, sect->neighbors[chain.b], edge.v1.x, edge.v1.y, edge.v2.x, edge.v2.y);
			chain.b++;
		}
		chain.a++;
	}
	return (1);
}

int     verify_map(t_engine *e)
{
	verify_vertex(e);
	verify_neighbor(e, NULL, NULL);
	verify_hull(e, NULL, NULL);
	return (1);
}
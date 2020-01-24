edges <- read.csv("~/Desktop/edges.csv")
head(edges)
nodes <- read.csv("~/Desktop/nodes.csv")
head(nodes)

library(igraph)
g <- graph_from_data_frame(d=edges, vertices=nodes, directed=TRUE)
V(g)$color[V(g)$type==1] <- "yellow"
V(g)$size <-6

E(g)$width <- E(g)$weight/5
E(g)$arrow.size <- 1
#plot(g, edges.size=edges$weight)
#plot(g, layout=layout_in_circle)
#plot(g, layout=layout_in_circle)
#plot(g, layout=layout_on_sphere)
plot(g, layout=layout_with_kk)
#plot(g, layout=layout_randomly)


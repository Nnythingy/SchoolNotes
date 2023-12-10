import networkx as nx
import glob
import itertools
import pandas as pd
from statistics import mean
import os

def make_network(location):
	"""
	Based on a list of co-ocurrences, this funciton reates a Gephi file and to spreadsheets:
	-node_info.xlsx node-level quantitative metrics
	-network_info.xlsx network-level quantitative metrics
    
    Args:
        location (string): A single .txt file or the directory with a collection of text files.      
    """
	
	#interpret location as either a .txt file or a directory
	if ".txt" in location:
		directory = location.replace(".txt","")
		files = [location]
	else:
		directory = location
		files = [x for x in glob.glob("%s/*.txt" % directory)]
	
	#new directory to store the results
	if not os.path.isdir("%s_analysis" % directory): os.mkdir("%s_analysis" % directory)
	
	#store information on all networks and all nodes
	networks_info = []
	nodes_info = []
	for fileitem in files:
		print("Processing %s" % fileitem)
		if ("/") in fileitem:
			filename = fileitem.split("/")[-1].replace(".txt","")
		elif ("\\") in fileitem:
			filename = fileitem.split("\\")[-1].replace(".txt","")
		else:
			filename = fileitem.replace(".txt","")
			
		#new network
		g = nx.Graph()
		
		#open the file and separate each line by commas
		for line in open(fileitem, encoding='utf-8', errors='ignore').readlines():
			items = [x.strip() for x in line.split(",")]
			
			#create an edge between each pair of items, if the edge exists increase by 1
			for subset in itertools.combinations(items, 2):
				if not g.has_edge(subset[0],subset[1]):
					g.add_edge(subset[0],subset[1],weight=1)
				else:
					g[subset[0]][subset[1]]["weight"]+=1
		
		#node-level measurements
		betweenness_centralities = nx.betweenness_centrality(g)
		eccentricities = nx.eccentricity(g)
		closeness = nx.closeness_centrality(g)
		
		# Networkx calculates the weighted betweeness centralities by default 
		# In order to obtain raw counts we multiply by max_shortest_paths

		max_shortest_paths = ((len(g)-1) * (len(g)-2))/2
		raw_betweenness_centralities = {k:v*max_shortest_paths for k,v in betweenness_centralities.items()}
		
		for n in g.nodes:
			g.nodes[n]["label"] = n
			nodes_info.append({
				"label":n,
				"degree":g.degree(n),
				"weighted_degree":g.degree(n,weight="weight"),
				"betweenness":raw_betweenness_centralities[n],
				"normalized_betweenness":betweenness_centralities[n],
				"eccentricity":eccentricities[n],
				"closeness":closeness[n],
				"network":filename
				})
		
		#create a gephi file for each network
		nx.write_gexf(g, "%s_analysis/%s.gexf" % (directory,filename))
		
		#network-level measurements
		networks_info.append({
			"network_id":filename,
			"nodes":len(g),
			"edges":g.size(),
			"avg path length":nx.average_shortest_path_length(g),
			"avg degree":mean([v for k,v in g.degree()]),
			"avg weighted degree":mean([v for k,v in g.degree(weight="weight")]),
			"diameter":nx.diameter(g),
			"radius":nx.radius(g),
			"density":nx.density(g)
			})
	
	#save Excel file with node info
	df = pd.DataFrame(nodes_info)
	df.to_excel("%s_analysis/nodeInfo.xlsx" % directory)
	
	#save Excel file with network info
	networks_info_df = pd.DataFrame(networks_info)
	networks_info_df.set_index("network_id",inplace=True)
	networks_info_df.to_excel("%s_analysis/networkInfo.xlsx" % directory,directory)

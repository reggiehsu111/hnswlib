import hnswlib


def create_100_data_points_around(num):
    data = [[x] for x in range(num - 50, num + 50)]
    labels = [x for x in range(num - 50, num + 50)]
    return data, labels


def dist(a, b):
    print("In dist")
    print(a, b)
    return 1.0


dim = 1
num_elements = 100
p = hnswlib.Index(dist_func=dist, dim=1)
p.init_index(max_elements=num_elements, ef_construction=20, M=10)

p.add_items(*create_100_data_points_around(50))
p.add_items(*create_100_data_points_around(250))
p.add_items([[110], [190]], [110, 190])
p.add_items([[120], [180]], [120, 180])
p.add_items([[130], [170]], [130, 170])
p.add_items([[140], [160]], [140, 160])

labels, distances = p.knn_query([145], k=10)

print(labels)
print(distances)

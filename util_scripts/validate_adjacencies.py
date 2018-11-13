import csv

def validate_row(idx, row):
    assert row, "Empty row on row {}".format(idx)


def validate_adjacencies(fpath = '../resources/adjacencies.csv'):
    graph = {}

    with open(fpath, 'r') as f:
        reader = csv.reader(f, delimiter=',', )
        for idx, row in enumerate(reader):
            if idx == 0:
                continue
            # No empty rows allowed
            assert row, "Empty row on row {}".format(idx)

            source = row[0]
            assert source.isdigit(), "Source {} is not a digit!".format(source)
            source = int(source)

            # Each source should have one and only one row
            assert source not in graph, "Duplicate source on line {0}!".format(idx)

            graph[source] = []

            for col in row:
                if col:
                    assert col.isdigit(), "{} is not blank and not a digit!".format(col)
                    graph[source].append(int(col))

    for src, dests in graph.items():
        for dest in dests:
            assert(dest in graph), "{0} links to {1}, but {1} doesn't appear in the graph!".format(src, dest)
            assert(src in graph[dest]), "{0} links to {1}, but {1} doesn't link to {0}!".format(src, dest)


if __name__ == '__main__':
    validate_adjacencies()
    print("All good!")

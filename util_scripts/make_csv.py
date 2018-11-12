territories = ["Alaska", "Alberta", "Central America", "Eastern United States", "Greenland", "Northwest Territory",
                "Ontario", "Quebec", "Western United States", "Argentina", "Brazil", "Peru", "Venezuela",
                "Great Britain", "Iceland", "Northern Europe", "Scandinavia", "Southern Europe", "Ukraine",
                "Western Europe", "Congo", "East Africa", "Egypt", "Madagascar", "North Africa", "South Africa",
                "Afghanistan", "China", "India", "Irkutsk", "Japan", "Kamchatka", "Middle East", "Mongolia", "Siam",
                "Siberia", "Ural", "Yakutsk", "Eastern Australia", "Indonesia", "New Guinea", "Western Australia"]

with open("test.csv", "w+") as f:
    for i in range(len(territories)):
        f.write('{:02d},{},,,,\n'.format(i, territories[i]))
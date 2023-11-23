import numpy as np
import matplotlib.pyplot as plt

def generate_dataset(num_points, d):
    return np.round(np.random.rand(num_points, d), 5)

def compute_distances(query_point, dataset):
    l1_distances = np.sum(np.abs(dataset - query_point), axis=1)
    l2_distances = np.sqrt(np.sum((dataset - query_point)**2, axis=1))
    linf_distances = np.max(np.abs(dataset - query_point), axis=1)
    return l1_distances, l2_distances, linf_distances

def compute_avg_ratios(nearest_distances, farthest_distances):
    return np.mean(farthest_distances / nearest_distances)

def main():
    num_points = 1000000
    dimensions = [1, 2, 4, 8, 16, 32, 64]
    num_queries = 100
    np.random.seed(42)  # for reproducibility

    avg_ratios_l1 = []
    avg_ratios_l2 = []
    avg_ratios_linf = []

    for d in dimensions:
        dataset = generate_dataset(num_points, d)
        query_indices = np.random.choice(num_points, num_queries, replace=False)
        query_points = dataset[query_indices]   
        avg_ratios_l1_d = []
        avg_ratios_l2_d = []
        avg_ratios_linf_d = []

        for query_point in query_points:
            l1_distances, l2_distances, linf_distances = compute_distances(query_point, dataset)

            # Exclude the query point itself from nearest data point computation
            min_l1_distance = np.min(l1_distances[l1_distances > 0])
            min_l2_distance = np.min(l2_distances[l2_distances > 0])
            min_linf_distance = np.min(linf_distances[linf_distances > 0])

            max_l1_distance = np.max(l1_distances)
            max_l2_distance = np.max(l2_distances)
            max_linf_distance = np.max(linf_distances)

            avg_ratios_l1_d.append(max_l1_distance / min_l1_distance)
            avg_ratios_l2_d.append(max_l2_distance / min_l2_distance)
            avg_ratios_linf_d.append(max_linf_distance / min_linf_distance)

        avg_ratios_l1.append(np.mean(avg_ratios_l1_d))
        avg_ratios_l2.append(np.mean(avg_ratios_l2_d))
        avg_ratios_linf.append(np.mean(avg_ratios_linf_d))

    # Plotting
    plt.plot(dimensions, avg_ratios_l1, label='L1 Norm')
    plt.plot(dimensions, avg_ratios_l2, label='L2 Norm')
    plt.plot(dimensions, avg_ratios_linf, label='L∞ Norm')

    plt.xlabel('Dimension (d)')
    plt.ylabel('Average Ratio of Farthest to Nearest Distances')
    plt.title('Average Ratio of Farthest to Nearest Distances vs. Dimension')
    plt.legend()
    # plt.yscale('log')  # Set y-axis to logarithmic scale
    plt.savefig(f'average_ratios_plot_dimensions4_logscale.png')
    # plt.show()
    plt.close()

if __name__ == "__main__":
    main()

#testing
# Now you can use the trained model for inference or further evaluation
import torch
import torch.nn as nn
import torch.optim as optim
from torch_geometric.nn import GCNConv
from torch_geometric.data import Data, DataLoader

class GCNModel(nn.Module):
    def __init__(self,input_dim, hidden_dim, output_dim):
        super(GCNModel, self).__init__()
        self.conv1 = GCNConv(input_dim, hidden_dim)
        self.conv2 = GCNConv(hidden_dim, output_dim)

    def forward(self,data):
        x, edge_index = data.x, data.edge_index
        x = self.conv1(x, edge_index)
        x = torch.relu(x)
        x = self.conv2(x, edge_index)
        return x.mean(dim=0)  # Aggregate node-level predictions to graph-level

def main():
    parser = argparse.ArgumentParser(description="Training a classification model")
    parser.add_argument("--model_path", required=True)
    parser.add_argument("--dataset_path", required=True)
    parser.add_argument("--val_dataset_path", required=True)
    args = parser.parse_args()
    print(f"Training a classification model. Output will be saved at {args.model_path}. Dataset will be loaded from {args.dataset_path}. Validation dataset will be loaded from {args.val_dataset_path}.")

    edges_path = args.dataset_path+'/edges.csv.gz'
    edge_features_path = args.dataset_path+'/edges_features.csv.gz'
    node_features_path = args.dataset_path+'/node_features.csv.gz'
    num_nodes_path = args.dataset_path+'/num_nodes.csv.gz'
    num_edges_path = args.dataset_path+'/num_edges.csv.gz'
    graph_labels_path = args.dataset_path+'/graph_labels.csv.gz'

    num_edges_reader = pd.read_csv(num_edges_path, compression='gzip')
    train_num_edges = num_edges_reader[num_edges_reader.columns[0]].tolist()

    num_nodes_reader = pd.read_csv(num_nodes_path, compression='gzip')
    train_num_nodes = num_nodes_reader[num_nodes_reader.columns[0]].tolist()

    graph_labels_reader = pd.read_csv(graph_labels_path, compression='gzip')
    train_graph_labels = graph_labels_reader[graph_labels_reader.columns[0]].tolist()

    edges_reader = pd.read_csv(edges_path, compression='gzip')
    train_edges = []
    start = 0
    for size in train_num_edges:
        grouped= []
        end = start+size
        for i in range(start,end):
            gg = edges_reader.iloc[i].tolist()
            grouped.append(gg)   
        train_edges.append(grouped)
        start+=size

    edge_features_reader = pd.read_csv(edge_features_path, compression='gzip')
    train_edge_features = []
    start = 0
    for size in train_num_edges:
        grouped= []
        end = start+size
        for i in range(start,end):
            gg = edges_reader.iloc[i].tolist()
            grouped.append(gg)   
        train_edge_features.append(grouped)
        start+=size

    node_features_reader = pd.read_csv(node_features_path, compression='gzip')
    train_node_features = []
    start = 0
    for size in train_num_nodes:
        grouped= []
        end = start+size
        for i in range(start,end):
            gg = edges_reader.iloc[i].tolist()
            grouped.append(gg)   
        train_edge_features.append(grouped)
        start+=size


    dataset=[]

    for i in range(len(train_num_nodes)):
        node_feature=[]
        edge_feature=[]
        edge_index=train_edges[i]
        graph_label=[train_graph_labels[i]]
        for j in range(len(train_node_features[i])):
            node_feature.append(train_node_features[i][j])
        for j in range(len(train_edge_features[i])):
            node_feature.append(train_edge_features[i][j])
        data = Data(x=torch.tensor(node_features, dtype=torch.float),
             edge_attr=torch.tensor(edge_features, dtype=torch.float),
             y=torch.tensor([graph_label], dtype=torch.long),
             edge_index=edge_index)
        dataset.append(data)
            
    dataloader = DataLoader(dataset, batch_size=1, shuffle=True)


    input_dim = 2  
    hidden_dim = 16
    output_dim = 2  
    model = GCNModel(input_dim, hidden_dim, output_dim)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=0.01)


    train_it = 50

    for i in range(train_it):
        total_loss = 0.0
        for data in dataloader:
            optimizer.zero_grad()
            output = model(data)
            loss = criterion(output.unsqueeze(0), data.y)  
            loss.backward()
            optimizer.step()
            total_loss += loss.item()

        average_loss = total_loss / len(dataloader)
        print(f'Epoch {i + 1}/{train_it}, Average Loss: {average_loss}')

    model.eval()

    predictions = []
    true_labels = []
    with torch.no_grad():
        for data in dataloader:
            output = model(data)
            
            print(output.shape)  
            
            if len(output.shape) == 1:  
                output = output.unsqueeze(0)
            
            predicted_class = torch.argmax(output, dim=1)  
            predictions.extend(predicted_class.cpu().numpy())
            true_labels.extend(data.y.cpu().numpy())


    from sklearn.metrics import accuracy_score

    accuracy = accuracy_score(true_labels, predictions)
    print(f'Accuracy on new dataset: {accuracy * 100:.2f}%')

if __name__=="__main__":
    main()

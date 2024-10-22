# Graph Analyzer with Interactive Interface¶
具體來說，這個 Analyzer 應該要支援下面這些指令：

- read <file name>
    - 我們實做的是無向圖（Undirected Graph），並且每個邊都會有對應的權重（Weight）
    - 讀取定義 Graph 的檔案，這個檔案的第一行是一個數字，表示總共有幾個 Vertex，緊接著一個二維陣列 使用 Adjacency Matrix 表示 Graph 的 Vertex 和 Edge 的關係
    - M[i, j] 代表 V<sub>i</sub> 和 V<sub>j</sub> 之間 Edge 的權重（Weight）
    - Example File

        5<br>
        0 &nbsp;5 &nbsp;4 &nbsp;0 &nbsp;1<br>
        5 &nbsp;0 &nbsp;7 &nbsp;2 &nbsp;1<br>
        4 &nbsp;7 &nbsp;0 &nbsp;3 &nbsp;3<br>
        0 &nbsp;2 &nbsp;3 &nbsp;0 &nbsp;6<br>
        1 &nbsp;1 &nbsp;3 &nbsp;6 &nbsp;0<br>
- minpath <v1> <v2>
    - 計算 V<sub>1</sub>和 V<sub>2</sub>之間的最短路徑的距離，輸出為一個自然數 
- mst
    - 輸出 Graph 的 Minimal-Spanning Tree 的所有 edge 的 weighted-sum
    - 輸出為一個自然數 
- help [command]
    - 輸出指令的詳細資訊和使用方法
    - 若使用者輸入 help，後面沒有跟著其他 argument 的話，則輸出所有支援的指令的資訊
    - 若使用者輸入 help cmd1 的話，則只要輸出 cmd1 的資訊即可
- quit
    - 退出程式
如果 Graph Analyzer 尚未讀取檔案的話，則 minpath 和 mst 指令都應該直接輸出 Please read the file first 這段文字。
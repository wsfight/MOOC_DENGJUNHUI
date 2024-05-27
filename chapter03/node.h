#define Posi(T) ListNode<T> *
template <typename T>
struct ListNode // 以双向链表模板实现
{
    T data;                           // 数值
    Posi(T) pred;                     // 其前驱结点
    Posi(T) succ;                     // 其后继结点
    // Posi(T) insertAsPred(T const &e); // 前驱插入
    // Posi(T) insertAsSucc(T const &e); // 后继插入
    ListNode()
    {
        this->pred = nullptr;
        this->succ = nullptr;
    }; // 默认构造
    ListNode(T const &e, Posi(T) p = nullptr, Posi(T) s = nullptr) : data(e), pred(p), succ(s){};
};

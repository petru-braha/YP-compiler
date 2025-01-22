class a
{
public:
    virtual ~a() = default;
    virtual char *evaluate() const = 0;
};

class b : public a
{
public:
    virtual ~b() = default;
};

class c : public b
{
public:
    virtual char *evaluate() const { return nullptr; };
};

int main()
{
    a *lala = new c();
    delete lala;
}

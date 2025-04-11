int main()
{
    Carte carte;
    try
    {
        BDD bdd("localhost", ......);
        carte = bdd.getCarte();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
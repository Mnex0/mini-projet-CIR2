int main()
{
    Carte carte;
    try
    {
        BDD bdd("hote", ......);
        carte = bdd.getCarte();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
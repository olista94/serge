common-settings
{
    ts
    {
        plugin                      pootle

        data
        {
            /*
            Provide the base API server URL here.
            Note that the trailing slash must be omitted.
            Options are:
            https://smartcat.ai       (Europe)
            https://us.smartcat.ai    (North America)
            https://ea.smartcat.ai    (Asia)
            You will know the server your account is on
            by just signing into your account
            and looking at the URL.
            */
            # base_url                https://smartcat.ai
            # executable          ~/.zing/

            project_id          common
            # token_id            prueba.pot
            # token               2020_08_common
        }
    }

    vcs
    {
        plugin                      git

        data
        {
            add_unversioned         YES
            clone_params            --depth 1
            email                   olista94@gmail.com
            name                    Oscar Lista
        }
    }

    job
    {
        /*
        Usually you want to have a single database for all your
        translation projects, unless you have multiple source languages.
        In that case it is recommended to split databases for each
        source language.
        */
        # (STRING) DBI-compatible connection string
        # Supported drivers: SQLite, MySQL and Postgres
        # SQLite sample: 'DBI:SQLite:dbname=/path/to/translate.db3'
        # SQLite sample: 'DBI:SQLite:dbname=:memory:' - in-memory database
        # for testing purposes
        # MySQL sample: 'DBI:mysql:database=translations'
        # MySQL sample: 'DBI:mysql:database=translations;host=localhost;port=3306'
        #
        # Note 1: SQLite database will be created automatically
        # if the target file does not exist
        # Note 2: Database will be initialized automatically if necessary

        # db_source                   DBI:SQLite:dbname=../db/translations.db3

        # db_source                   DBI:Pg:dbname=pootledb;host='172.18.0.4';port=5432

        db_source                   DBI:SQLite:dbname=../db/translations.db3

        # db_username                 pootle
        # db_password                 astupidpassword
        # db_namespace                pootledb
        /*
        Source language must be recognized by Smartcat.
        See https://smartcat.ai/Home/Languages
        */
        source_language                         en
        output_bom                              NO
        use_keys_as_context                     YES
    }
}

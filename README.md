Clone or download this project into any local folder and use it to bootstrap your first continuous localization project with Serge and Pootle:

```
git clone https://github.com/olista94/serge.git
```


# Getting Started Guide

## Getting Around

This repository contains a sample project, `prueba`. First things to do are:

-   See the configuration file: [configs/prueba.serge](configs/prueba.serge)
-   Look at the contents of the source project folder: [vcs/prueba](vcs/prueba)

This sample project is set up to have `en` (English) as a source language, `es` and `gl` as target languages, and will process all keys in .po/.pot resource files in [vcs/prueba/en](vcs/prueba/en) directory.

## Initial Run

Go to `configs` directory and run the localization step:

```
serge localize
```

This will create localized files under `vcs/prueba/es` and `vcs/prueba/gl` directories. These files will have English content, since translations have not been provided just yet.

The same localization step will generate translation files under `ts/prueba/es` and `ts/prueba/gl` directories. You can examine the generated `.po` files and also see their initial state with no translations.

## Doing Translations Locally

Edit e.g. `ts/prueba/es/example..po/.pot.po` file and provide a translation for a single string (for testing purposes, any random "translation" will work).

Run `serge localize` once again from the `configs` directory. If you now open the localized resource file, e.g. `vcs/prueba/es/example.po`, you will see that your translation has been integrated into the .po/.pot file.

## Connecting with Pootle

1. Create a new project in Pootle with _English_ as a source language.
2. Edit the [configs/common.serge.inc](configs/common.serge.inc) file and fill out your account parameters and credentials under _common-settings → ts_ config section: `base_url`, `token_id`, and `token`. Instructions next to each parameter will help you understand where to get the values from. Once defined, these settings will be shared across your future localization projects.
3. Edit the [configs/prueba.serge](configs/prueba.serge) file and specify the `project_id`, following the instructions in the configuration file.

Now you can push your translation files to Pootle:

```
serge push-ts
```

Go to Pootle, open the project you created, and there you will see your all `.po` files.

Open e.g. `example.po` and edit the translation for the string that you translated previously.

Now you can pull translations from Pootle and run a localization cycle at once:

```
serge pull-ts localize
```

If you now open the localized resource file, `po/prueba/es/example.po`, you will see that the new translation has been integrated into the .po/.pot file.

## Running Localization Continuously

This project has two convenience scripts, [sync-once.sh](sync-once.sh) and [sync-loop.sh](sync-loop.sh) that you can use as a starting point for your continuous localization process.

-   Run `./sync-once.sh` to run the sync/localization cycle just once.
-   Run `./sync-loop.sh` to run the sync/localization cycle every 5 minutes. You can edit the file and put any delay you want.

While the localization is running in background (eventually you will want to run it on a dedicated server), you can modify your example project (add or delete source .po/.pot files, add, change or delete keys in those .po/.pot files) and provide translations on Pootle side at the same time, and Serge will merge in all these changes, gathering the new translations, updating the localized resources, and pushing new strings for translation.

## Adding VCS Synchronization

The last missing step is to make Serge not only generate the localized files locally, but also pull the sources from your actual source code repository, and push localized files back to the remote repo. Since Git is the most popular version control system, this sample project includes a stub for connecting to a Git repo.

Edit the `configs/prueba.serge` file so that _→ sync → vcs → data →_ `remote_path` parameter points to the actual remote repository URL. Now initialize the data from the remote repo (this will remove the previous contents of `vcs/prueba` folder with the contents of your repository):

```
serge pull --initialize prueba.serge
```

The `--initialize` parameter in this command is needed only once, when you want to delete and re-populate the contents of the project folder.

Now your project has a different directory structure, and maybe different files (not .po/.pot), so you need to edit your `configs/prueba.serge` file accordingly (see _→ jobs → (first job section) →_ `source_dir`, `source_match`, `output_file_path` parameters, and the `parser` section). At this point we recommend you to spend some time reading the [Serge documentation](https://serge.io/docs/) for the list of available parsers and their parameters, and the [configuration file syntax and reference](https://serge.io/docs/configuration-files/syntax/).

Once you have your job parameters tweaked, it's time to test this by running a localization cycle once again, and also cleaning up the outdated translation files:

```
serge localize
serge clean-ts
```

If you see that a set of localized files was properly created in your `vcs/prueba` folder, and that translation files in `ts/prueba` folder also look good, you can push the localized files back to the remote repository:

```
serge push
```

The last and final step is to enable the full synchronization cycle. Edit the `sync-once.sh` script by disabling the `serge pull-ts localize push-ts` line and enabling the `serge sync` line. The latter command is equivalent to `serge pull pull-ts localize push-ts push`. In human language, this means that running `serge sync` will do everything a continuous localization is expected to do: pull the new contents from both your Git server and Pootle, update localized resources and translation files, and push changes back to Git and Pootle, respectively.

Finally, run:

```
./sync-loop.sh
```

Congratulations! You now live in the world of smooth continuous localization _(press Ctrl+C anytime to get back to reality)_.

## Adding new projects

In the paradigm of continuous localization, your Pootle projects will be permanent; content in these projects will be constantly updated, reflecting the changes in your repositories and external content sources. You can create one project for your iOS application, another one for Android, for your website, documentation, and so on. To set up a new project (besides creating one in Pootle), you will need to make a copy of `configs/prueba.serge` to `configs/project-b.serge` (of course, file and project names are up to you), and edit a new configuration file accordingly.

## Unlocking the true power of Serge

With Serge as a continuous localization solution, you have an unprecedented flexibility and power. Some ideas that might inspire you are:

-   Automatic discovery and localization of multiple product branches
-   Ability to prohibit localized file updates unless they are 100% translated (handy for marketing materials!)
-   Ability to specify target languages right in each file, to enable automated self-service scenarios
-   Pseudo-localization for easier internationalization (i18n) QA
-   Conditional exclusion of certain strings by mask
-   Ability to auto-generate comments and preview links for each string
-   Ability to group multiple repositories and different file types under a same logical project
-   Ability to preprocess source files for greater flexibility
-   Ability to post-process localized files so that the final result is CI/CD-ready
-   Ability to email developers if source files are broken
-   ... and much more!

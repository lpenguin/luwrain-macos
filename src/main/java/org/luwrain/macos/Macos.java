package org.luwrain.macos;

import org.luwrain.os.Location;

import java.io.File;

/**
 * Created by nikita on 21.03.15.
 */
public class Macos implements org.luwrain.os.OperatingSystem {
    private static final String LUWRAIN_MACOS_LIBRARY_NAME = "luwrainmacos";

    @Override
    public String init() {
        System.loadLibrary(LUWRAIN_MACOS_LIBRARY_NAME);
        return null;
    }

    @Override public Location[] getImportantLocations()
    {
        return ImportantLocations.getImportantLocations();
    }

    @Override public File getRoot(File relativeTo)
    {
        return new File("/");
    }
}

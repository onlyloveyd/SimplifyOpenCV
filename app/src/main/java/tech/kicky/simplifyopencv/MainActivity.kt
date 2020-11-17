package tech.kicky.simplifyopencv

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import tech.kicky.simplifyopencv.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    private val mBinding by lazy { ActivityMainBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(mBinding.root)

        mBinding.ivLena.setImageResource(R.drawable.lena)
        val image = BitmapFactory.decodeResource(resources, R.drawable.lena)
            .copy(Bitmap.Config.ARGB_8888, true)
        val width = image.width
        val height = image.height
        val pixel = IntArray(width * height)
        image.getPixels(pixel, 0, width, 0, 0, width, height)
        val grayPixels: IntArray? = doGray(pixel, width, height)

        val grayBp = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
        grayBp.setPixels(grayPixels, 0, width, 0, 0, width, height)
        mBinding.ivResult.setImageBitmap(grayBp)
    }

    private external fun doGray(imgData: IntArray?, width: Int, height: Int): IntArray?

}